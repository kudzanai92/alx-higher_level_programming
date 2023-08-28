#!/usr/bin/python3

def safe_print_list(my_list=[], x=0):
    """Print x elements of a list.

    Args:
        my_list (list): The list to print elements from.
        x (int): The number of elements of my_list to print.

    Returns:
        The number of elements printed.
    """
    try:
        elements_to_print = my_list[:x]
        print("".join(map(str, elements_to_print)))
        return len(elements_to_print)
    except Exception as e:
        print(f"An error occurred: {e}")
        return (0)
