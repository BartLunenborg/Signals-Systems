use crate::Signal;
use std::fs::{self, File};
use std::io::{BufRead, BufReader, Cursor};

#[test]
/// The testcases directory contains 10 `.in` and `.out` files.
/// Each `in` file contains 2 inputs for a Signal.
/// Each `out` file contains the result of convolving the two Signals.
/// This test creates two `Signals` from the `.in` file and checks if
/// the convolution of the two is equal to the known result in the `.out` file.
fn test_1_10() {
    for i in 1..11 {
        let n = i.to_string();

        let f = File::open(format!("./testcases/{}.in", n)).unwrap();
        let f = BufReader::new(f);
        let input: Vec<String> = f.lines().map(|line| line.unwrap()).collect();

        let x = Signal::new(Cursor::new(&input[0]));
        let y = Signal::new(Cursor::new(&input[1]));
        let z = x.convolve(&y);

        let ans = fs::read_to_string(format!("./testcases/{}.out", n)).unwrap();
        let ans = Signal::new(Cursor::new(ans));

        assert_eq!(z.len(), ans.len());
        for (i, c) in z.data().into_iter().enumerate() {
            assert_eq!(c.re.round(), ans.data()[i].re);
        }
    }
}
