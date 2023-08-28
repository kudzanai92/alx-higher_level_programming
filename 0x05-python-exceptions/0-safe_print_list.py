#!/usr/bin/env python3

def safe_print_list(my_list=[], x=0):
    count = 0  # Initialize a counter to keep track of printed elements

    try:
        for element in my_list:
            if count < x:
                print(element, end=' ')  # Print the element on the same line
                count += 1
        print()  # Add a new line after printing all elements
    except TypeError:  # Handle the case where my_list is not iterable
        print("Error: my_list is not iterable")

    return count  # Return the real number of elements printed


# Example usage:
my_list = [1, 2, 3, 4, 5]
x = 3
elements_printed = safe_print_list(my_list, x)
print(f"Number of elements printed: {elements_printed}")
