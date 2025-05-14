#!/usr/bin/python3
""" Module : count_it """

import re
import requests

def count_words(subreddit, word_list, after=None, counts=None):
    """ recursive function that queries the Reddit API """

    if counts is None:
        # Normalize word list to lowercase and handle duplicates
        unique_words = sorted(set(word.lower() for word in word_list))
        counts = {word: 0 for word in unique_words}
        word_list = unique_words
    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    headers = {'User-Agent': 'recursive-keyword-counter'}
    params = {'limit': 100}
    if after:
        params['after'] = after

    response = requests.get(url, headers=headers, params=params, allow_redirects=False)

    # Invalid subreddit (404 or redirect)
    if response.status_code != 200:
        return

    data = response.json().get('data', {})
    posts = data.get('children', [])
    after = data.get('after', None)

    for post in posts:
        title = post['data']['title'].lower()
        words = re.findall(r'\b\w+\b', title)
        for word in word_list:
            counts[word] += words.count(word)

    if after:
        return count_words(subreddit, word_list, after, counts)
    else:
        # Filter out 0 counts, sort by count desc, then word asc
        filtered = {k: v for k, v in counts.items() if v > 0}
        sorted_counts = sorted(filtered.items(), key=lambda x: (-x[1], x[0]))
        for word, count in sorted_counts:
            print(f"{word}: {count}")