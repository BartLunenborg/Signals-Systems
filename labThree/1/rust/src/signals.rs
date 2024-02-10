use std::{f64::consts::PI, io::{self, BufRead}};
use num_complex::Complex64;

/// Represents a signal with a length and data.
pub struct Signal {
    /// The length of the signal.
    length: i32,
    /// The data of the signal, as a Vec<Complex64>.
    data: Vec<Complex64>
}

/// Reads a signal from standard input.
/// The signal should be formatted:
/// ```
/// n: [1,2,3,..,n]
/// let s: Signal = read_signal();
/// ```
pub fn read_signal() -> Signal {
    let mut line = String::new();
    let stdin = io::stdin();
    stdin.lock()
        .read_line(&mut line)
        .unwrap();

    let (length, data) = line.split_once(":").unwrap();
    let length = length
        .trim()
        .parse::<i32>()
        .unwrap();
    let data: Vec<Complex64> = data
        .trim()
        .trim_start_matches("[")
        .trim_end_matches("]")
        .split(",")
        .filter_map(|c| c.parse().ok())
        .collect();

    Signal { length, data}
}

/// Prints a Signal to standard output.
/// # Examples
/// ```
/// let s: Signal = Signal { 
///     length: 5, 
///     data: vec![
///     Complex64::new(1.0, 1.0),
///     Complex64::new(2.0, 2.0),
///     Complex64::new(3.0, 3.0),
///     Complex64::new(4.0, 4.0),
///     Complex64::new(5.0, 5.0),
///     ],
/// };
/// print_signal(&s);
/// // Output: 5: [1,2,3,4,5]
/// ```
pub fn print_signal(s: &Signal) {
    let formatted_data: String = s.data
        .iter()
        .map(|x| x.re.round() as i32)
        .map(|x| x.to_string())
        .collect::<Vec<String>>()
        .join(",");
    println!("{}: [{}]", s.length, formatted_data);
}

/// finds the smallest number >= n that is a power of 2
fn power_of_two(n: i32) -> i32 {
    if n & (n - 1) != 0 {
        let mut p2: i32 = 1;
        while p2 < n {
            p2 <<= 1;
        }
        p2
    } else {
        n
    }
}

/// Cooley and Tukey fft algorithm
fn fft(s: Signal, omega: Complex64) -> Signal {
    let n: i32 = s.length;
    if n == 1 {
        return s;
    }

    let mut x: Complex64 = Complex64 {re: 1.0, im: 0.0};

    let odd: Vec<_> = s.data.iter().skip(1).step_by(2).cloned().collect();
    let even: Vec<_> = s.data.iter().step_by(2).cloned().collect();

    let odd_fft = fft(Signal {length: n / 2, data: odd }, omega * omega);
    let even_fft = fft(Signal {length: n / 2, data: even }, omega * omega);
    
    let un: usize = n.try_into().unwrap();
    let mut result: Vec<_> = vec![Complex64 {re: 0.0, im: 0.0}; un];

    for i in 0..(un / 2) {
        result[i] = even_fft.data[i] + x * odd_fft.data[i];
        result[i+un/2] = even_fft.data[i] - x * odd_fft.data[i];
        x *= omega;
    }

    Signal {length: n, data: result}
}

/// Creates a new Signal of length n.
/// The new data will be padded with 0's to fill.
fn pad_signal(s: &Signal, n: i32) -> Signal {
    let mut padded_data = s.data.clone();
    padded_data.resize_with(n.try_into().unwrap(), || num_complex::Complex::new(0.0, 0.0));
    Signal { length: n, data: padded_data }
}

/// Given two Signals, return the convolution calculated with the fft.
pub fn convolve(x: &Signal, y: &Signal) -> Signal {
    let length = x.length + y.length - 1;
    let n = power_of_two(length);

    // pad x and y with 0's
    let x_padded: Signal = pad_signal(x, n);
    let y_padded: Signal = pad_signal(y, n);

    // fft of padded x and y
    let omega: Complex64 = Complex64::from_polar(1.0, 2.0 * PI / n as f64);
    let xfft = fft(x_padded, omega);
    let yfft = fft(y_padded, omega);

    // component multiply
    let xy: Vec<_> = xfft.data.iter()
        .zip(yfft.data.iter())
        .map(|(x, y)| x * y)
        .collect();

    // inverse fft and adjust by / n
    let result: Vec<_> = fft(Signal {length: n, data: xy}, omega.conj()).data.iter()
        .map(|num| num / n as f64)
        .collect();

    Signal {length, data: result[..length as usize].to_vec()}
}
