mod signals;
use std::io;

use signals::Signal;

fn main() {
    let x = Signal::new(io::stdin().lock());
    let y = Signal::new(io::stdin().lock());
    let z = x.convolve(&y);
    z.print();
}
