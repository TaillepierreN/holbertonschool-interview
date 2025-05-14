#!/usr/bin/python3
"""
0-count.py - Count occurrences of keywords in Reddit hot article titles recursively.
"""
import requests
import sys


def count_words(subreddit, word_list, after=None, count_dict=None):
    """
        Recursively count occurrences of keywords in Reddit hot article titles.
        subreddit: The subreddit to query.
        word_list: The list of keywords to count.
        after: Used for pagination. If None, this is the first call to the function.
        count_dict: Tracks the count of each keyword across recursive calls.
    """
    if count_dict is None:
        # Initialize count dictionary
        count_dict = {}
        for word in word_list:
            lower_word = word.lower()
            count_dict[lower_word] = count_dict.get(lower_word, 0)

    # Prepare the API URL
    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    headers = {'User-Agent': 'holbi-keyword-counter'}
    params = {'limit': 100}
    if after:
        params["after"] = after

    try:
        # Send the GET request
        response = requests.get(url, headers=headers,
                                params=params, allow_redirects=False)
        response.raise_for_status()
        data = response.json().get("data", {})
        after = data.get("after", None)
        posts = data.get("children", [])

        # Count keywords in titles
        for post in posts:
            title = post.get("data", {}).get("title", "").lower().split()
            for word in title:
                cleaned_word = ''.join(char for char in word if char.isalpha())
                if cleaned_word in count_dict:
                    count_dict[cleaned_word] += 1

        # Continue recursively if there are more posts
        if after is not None:
            count_words(subreddit, word_list, after, count_dict)
        else:
            # Print sorted results
            sorted_counts = sorted(
                [(word, count)
                 for word, count in count_dict.items() if count > 0],
                key=lambda x: (-x[1], x[0])
            )
            for word, count in sorted_counts:
                print(f"{word}: {count}")
    except requests.RequestException as e:
        # Print to stderr
        print(f"Error fetching data from Reddit: {e}", file=sys.stderr)
