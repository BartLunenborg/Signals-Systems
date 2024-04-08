from math import pi
import cmath


class Signal:
    """
    Represents a Signal:
        length: int
        signal: List[[complex]]
    """
    def __init__(self, length: int, signal: list[complex]):
        self.length = length
        self.signal = signal

    def print(self):
        """
        Print the array of Signal to std.out formatted:
        >>> n: [1,2,3,...,n]
        """
        nums = ",".join([str(int(round(n.real))) for n in self.signal])
        print(f"{self.length}: [{nums}]")

    @classmethod
    def read_new_signal(cls) -> 'Signal':
        """
        Create a Signal instance given a string read from the std.in formatted
        >>> n: [1,2,3,...,n]
        """
        n, array = input().strip().split(": ")
        return cls(int(n), [complex(num) for num in array[1:len(array)-1].split(",")])


# Cooley and Tukey fft algorithm implementation
def _fft(omega: complex, s: Signal) -> Signal:
    if s.length == 1:
        return s

    n, x = s.length, 1
    y_even = _fft(omega**2, Signal(n // 2, s.signal[::2]))
    y_odd = _fft(omega**2, Signal(n // 2, s.signal[1::2]))

    array = [0j] * n
    for i in range(n//2):
        array[i] = y_even.signal[i] + x * y_odd.signal[i]
        array[i + n//2] = y_even.signal[i] - x * y_odd.signal[i]
        x *= omega

    return Signal(n, array)


def convolve(x: Signal, y: Signal) -> Signal:
    """
    Given Signal x and y, returns the convolution Signal z.
    The fft algorithm is used to calculate z.
    """
    # n and length of z
    n, z_len = 2, x.length + y.length - 1

    # adjust length n needed for fft
    while (n < z_len):
        n <<= 2

    # omega for fft
    omega = cmath.exp(2j * pi / n)

    # fft of x and y
    x_fft = _fft(omega, Signal(n, x.signal + [0] * (n - x.length)))
    y_fft = _fft(omega, Signal(n, y.signal + [0] * (n - y.length)))

    # ifft of x_fft * y_fft
    z = _fft(omega.conjugate(), Signal(n, [a * b for a, b in zip(x_fft.signal, y_fft.signal)]))

    # return z adjusted back to correct length
    return Signal(z_len, [num / n for num in z.signal[:z_len]])
