use std::{error::Error, fmt::Display, io};
pub mod ppm;
pub mod steganograpy;

pub trait Image {
    fn open(path: &str) -> io::Result<Self>
    where
        Self: std::marker::Sized;
    fn save(&self, path: &str) -> io::Result<()>
    where
        Self: std::marker::Sized;
}

#[derive(Debug)]
pub enum ImageError {
    Io(io::Error),
    InvalidFormat,
    InvalidArgument,
    MessageTooLongForImage,
}

impl Display for ImageError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            ImageError::Io(e) => write!(f, "IO error: {}", e),
            ImageError::InvalidFormat => write!(f, "Invalid image format"),
            ImageError::InvalidArgument => write!(f, "Invalid argument"),
            ImageError::MessageTooLongForImage => write!(f, "Message too long for image"),
        }
    }
}

impl Error for ImageError {}
