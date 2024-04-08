from signals import *


def main():
    z = convolve(Signal.read_new_signal(), Signal.read_new_signal())
    z.print()


if __name__ == "__main__":
    main()
