use std::ops::BitAnd;

use crate::ImageError;

pub fn get_lsb<N>(n: N) -> N
where
    N: BitAnd<Output = N> + TryFrom<u8>,
{
    n & 1u8.try_into().unwrap_or_else(|_| unreachable!())
}

pub fn hide_char(char: u8, bytes: &mut [u8]) {
    assert!(bytes.len() == 8);
    let mut char = char.to_le();
    for byte in bytes {
        if get_lsb(char) == 1 {
            if get_lsb(*byte) == 0 {
                *byte |= 0b0000_0001;
            }
        } else if get_lsb(*byte) == 1 {
            *byte &= 0b1111_1110;
        }
        char >>= 1;
    }
}

pub fn reveal_char(bytes: &[u8]) -> u8 {
    assert!(bytes.len() == 8);
    let mut char = 0;
    for byte in bytes.iter().rev() {
        char <<= 1;
        char |= get_lsb(*byte);
    }
    char.to_be()
}

pub trait Steganograpy {
    fn hide(&mut self, message: &str) -> Result<(), ImageError>;
    fn reveal(&self) -> String;
}

#[cfg(test)]
mod tests {
    use crate::steganograpy::{hide_char, reveal_char};

    #[test]
    fn hide_reveal_char() {
        let mut bytes = [0; 8];
        hide_char(b'\0', &mut bytes);
        assert_eq!(reveal_char(&bytes), b'\0');
    }
}
