from signals import *


def main():
    z = fft(readSignal(), readSignal())
    z.print()


if __name__ == "__main__":
    main()
