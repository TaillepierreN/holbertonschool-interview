#!/usr/bin/python3
"""
    Continuously reads input lines and processes them to compute metrics:
"""
import sys

total_file_size = 0
line_count = 0
valid_status_codes = ['200', '301', '400', '401', '403', '404', '405', '500']
status_code_count = {code: 0 for code in valid_status_codes}
has_printed_final = False

def print_metrics():
    """

    Prints the computed metrics to stdout.
    """
    print(f"File size: {total_file_size}")
    for status_code in sorted(valid_status_codes):
        if status_code_count[status_code] > 0:
            print(f"{status_code}: {status_code_count[status_code]}")

if __name__ == "__main__":
    try:
        has_printed_final = False

        for line in sys.stdin:
            words = line.split()

            if len(words) >= 2:
                status_code = words[-2]
                try:
                    file_size = int(words[-1])
                    total_file_size += file_size
                except ValueError:
                    continue
                if status_code in status_code_count:
                    status_code_count[status_code] += 1

                line_count += 1

                if line_count % 10 == 0:
                    print_metrics()
                    has_printed_final = True

        if not has_printed_final or line_count % 10 != 0:
            print_metrics()


    except KeyboardInterrupt:
        print_metrics()
        raise
