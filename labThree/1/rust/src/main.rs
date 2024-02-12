mod signals;
use signals::{convolve, print_signal, read_signal};

fn main() {
    let x = read_signal();
    let y = read_signal();
    let z = convolve(&x, &y);
    print_signal(&z);
}
