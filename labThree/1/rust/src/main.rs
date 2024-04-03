mod signals;
use signals::{convolve, read_signal};

fn main() {
    let x = read_signal();
    let y = read_signal();
    let z = convolve(&x, &y);
    z.print_signal();
}
