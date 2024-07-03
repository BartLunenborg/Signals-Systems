use num_complex::Complex64;
use std::{f64::consts::PI, io};

/// Represents a signal with a length and data.
pub struct Signal {
    /// The length of the signal.
    length: i32,
    /// The data of the signal, as a `Vec<Complex64>`.
    data: Vec<Complex64>,
}

impl Signal {
    /// Reads a signal of length `n` from a reader that implements `BufRead`.
    /// The input should be formatted:
    /// `n: [1,2,3,..,n]`
    /// # Example
    /// ```
    /// # use std::io;
    /// # use fft::Signal;
    /// # use num_complex::Complex;
    /// let reader = io::Cursor::new("4: [6,2,3,4]");
    /// let s: Signal = Signal::new(reader);
    /// assert_eq!(s.len(), 4);
    /// assert_eq!(
    ///     s.data().clone(),
    ///     vec![
    ///         Complex::new(6.0, 0.0),
    ///         Complex::new(2.0, 0.0),
    ///         Complex::new(3.0, 0.0),
    ///         Complex::new(4.0, 0.0),
    ///     ]
    /// );
    /// ```
    pub fn new(mut reader: impl io::BufRead) -> Self {
        let mut line = String::new();
        reader.read_line(&mut line).unwrap();

        let (length, data) = line.split_once(':').unwrap();
        let length = length.trim().parse::<i32>().unwrap();
        let data: Vec<Complex64> = data
            .trim()
            .trim_start_matches('[')
            .trim_end_matches(']')
            .split(',')
            .filter_map(|c| c.parse().ok())
            .collect();

        Signal { length, data }
    }

    /// Get the length of the `data` vector of `Signal`.
    pub fn len(&self) -> i32 {
        self.length
    }

    /// Get a reference to the `data` vector.
    pub fn data(&self) -> &Vec<Complex64> {
        &self.data
    }

    /// Creates a new Signal of length n padded with 0's
    fn pad_signal(&self, n: i32) -> Self {
        let mut padded_data = self.data.clone();
        padded_data.resize(n as usize, Complex64 { re: 0.0, im: 0.0 });
        Signal {
            length: n,
            data: padded_data,
        }
    }

    /// Cooley and Tukey fft algorithm
    pub fn fft(&self, omega: Complex64) -> Self {
        let n: i32 = self.length;
        if n == 1 {
            return Signal {
                length: 1,
                data: self.data.clone(),
            };
        }

        let odd = Signal {
            length: n / 2,
            data: self.data.iter().skip(1).step_by(2).cloned().collect(),
        }
        .fft(omega * omega);

        let even = Signal {
            length: n / 2,
            data: self.data.iter().step_by(2).cloned().collect(),
        }
        .fft(omega * omega);

        let mut result = vec![Complex64 { re: 0.0, im: 0.0 }; n as usize];
        let mut x = Complex64 { re: 1.0, im: 0.0 };
        let half_n = (n / 2) as usize;

        for i in 0..half_n {
            result[i] = even.data[i] + x * odd.data[i];
            result[i + half_n] = even.data[i] - x * odd.data[i];
            x *= omega;
        }

        Signal {
            length: n,
            data: result,
        }
    }

    /// Given two Signals, returns the convolution calculated using the fft.
    pub fn convolve(&self, y: &Signal) -> Self {
        let z_length = self.length + y.length - 1;
        let mut n = z_length;
        if n & (n - 1) != 0 {
            n = 1;
            while n < z_length {
                n <<= 1;
            }
        }

        let omega: Complex64 = Complex64::from_polar(1.0, 2.0 * PI / n as f64);
        let z_vec: Vec<_> = Signal {
            length: n,
            data: self
                .pad_signal(n)
                .fft(omega)
                .data
                .iter()
                .zip(y.pad_signal(n).fft(omega).data.iter())
                .map(|(x, y)| x * y)
                .collect(),
        }
        .fft(omega.conj())
        .data
        .iter()
        .map(|x| x / n as f64)
        .collect();

        Signal {
            length: z_length,
            data: z_vec[..z_length as usize].to_vec(),
        }
    }
}

#[cfg(test)]
mod tests;
