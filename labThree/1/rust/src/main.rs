mod signals;
use signals::{print_signal, read_signal, convolve};

fn main() {
    let x = read_signal();
    let y = read_signal();
    let z = convolve(&x, &y);
    print_signal(&z);
}
