#!/usr/bin/python3
"""
    Continuously reads input lines and processes them to compute metrics:
    1. Reads and splits each line by spaces.
    2. Skips lines that don't meet the required format or aren't "GET" requests.
    3. Extracts the status code and file size, skipping lines with invalid file sizes.
    4. Updates the total file size and counts occurrences of valid status codes.
    5. Prints metrics after every 10 processed lines.
    6. Handles end of input (EOF) or keyboard interruption (CTRL + C).
"""
total_file_size = 0
status_code_count = {}
line_count = 0
valid_status_codes = ['200', '301', '400', '401', '403', '404', '405', '500']


def print_metrics():
    """
        Prints the computed metrics to stdout.
    """
    print(f"File size: {total_file_size}")
    for status_code in sorted(valid_status_codes):
        if status_code in status_code_count:
            print(f"{status_code}: {status_code_count[status_code]}")

try:
    while True:
        try:
            line = input().strip()
            parts = line.split(' ')
            
            if len(parts) < 7 or not parts[5].startswith('"GET'):
                continue

            status_code = parts[-2]
            try:
                file_size = int(parts[-1])
            except ValueError:
                continue

            total_file_size += file_size
            if status_code in valid_status_codes:
                if status_code in status_code_count:
                    status_code_count[status_code] += 1
                else:
                    status_code_count[status_code] = 1

            line_count += 1


            if line_count % 10 == 0:
                print_metrics()

        except EOFError:
            break

except KeyboardInterrupt:
    pass


print_metrics()
