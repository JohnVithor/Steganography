use crate::{
    steganograpy::{hide_char, reveal_char, Steganograpy},
    Image, ImageError,
};
use std::{
    fs::File,
    io::{self, BufRead, BufReader, Read, Seek, SeekFrom, Write},
};

pub struct PPM {
    id: String,
    width: usize,
    height: usize,
    max: u8,
    comment: Option<String>,
    data: Vec<u8>,
}

fn get_id(reader: &mut BufReader<File>) -> Result<String, io::Error> {
    let mut id = String::new();
    let r = reader.read_line(&mut id)?;
    if r == 0 {
        return Err(io::Error::new(io::ErrorKind::Other, "Empty file"));
    }
    Ok(id.trim().to_string())
}

fn get_comment(reader: &mut BufReader<File>) -> Result<Option<String>, io::Error> {
    let mut comment = String::new();
    let r = reader.read_line(&mut comment)?;
    if r == 0 {
        return Err(io::Error::new(io::ErrorKind::Other, "Empty file"));
    }
    if comment.starts_with('#') {
        Ok(Some(comment.strip_prefix('#').unwrap().trim().to_string()))
    } else {
        reader.seek(SeekFrom::Current(-(comment.len() as i64)))?;
        Ok(None)
    }
}

fn get_width_height(reader: &mut BufReader<File>) -> Result<(usize, usize), io::Error> {
    let mut width_height = String::new();
    let r = reader.read_line(&mut width_height)?;
    if r == 0 {
        return Err(io::Error::new(io::ErrorKind::Other, "Empty file"));
    }
    let mut width_height = width_height.split_whitespace();
    let width = if let Some(width) = width_height.next() {
        width
            .trim()
            .parse::<usize>()
            .map_err(|_| io::Error::new(io::ErrorKind::Other, "Invalid file"))
    } else {
        return Err(io::Error::new(io::ErrorKind::Other, "Invalid file"));
    }?;
    let height = if let Some(height) = width_height.next() {
        height
            .trim()
            .parse::<usize>()
            .map_err(|_| io::Error::new(io::ErrorKind::Other, "Invalid file"))
    } else {
        return Err(io::Error::new(io::ErrorKind::Other, "Invalid file"));
    }?;
    Ok((width, height))
}

fn get_max(reader: &mut BufReader<File>) -> Result<u8, io::Error> {
    let mut max = String::new();
    let r = reader.read_line(&mut max)?;
    if r == 0 {
        return Err(io::Error::new(io::ErrorKind::Other, "Empty file"));
    }
    let max = max
        .trim()
        .parse::<u8>()
        .map_err(|_| io::Error::new(io::ErrorKind::Other, "Invalid file"))?;
    Ok(max)
}

fn get_data(
    reader: &mut BufReader<File>,
    width: usize,
    height: usize,
) -> Result<Vec<u8>, io::Error> {
    let mut data = vec![];
    for _ in 0..height {
        for _ in 0..width {
            let mut buf = [0; 3];
            reader.read_exact(&mut buf)?;
            data.extend(buf)
        }
    }
    Ok(data)
}

impl PPM {
    pub fn new(
        id: &str,
        comment: Option<String>,
        width: usize,
        height: usize,
        max: u8,
        data: Vec<u8>,
    ) -> Result<Self, ImageError> {
        if data.len() != width * height * 3 {
            return Err(ImageError::InvalidArgument);
        }
        Ok(Self {
            id: id.to_string(),
            comment,
            width,
            height,
            max,
            data,
        })
    }
    pub fn id(&self) -> &str {
        &self.id
    }
    pub fn width(&self) -> usize {
        self.width
    }
    pub fn height(&self) -> usize {
        self.height
    }
    pub fn max(&self) -> u8 {
        self.max
    }
    pub fn data(&self) -> &[u8] {
        &self.data
    }
}

impl Image for PPM {
    fn open(path: &str) -> io::Result<Self> {
        let f = File::open(path)?;
        let mut reader = BufReader::new(f);
        let id = get_id(&mut reader)?;
        let comment = get_comment(&mut reader)?;
        let (width, height) = get_width_height(&mut reader)?;
        let max = get_max(&mut reader)?;
        let data = get_data(&mut reader, width, height)?;
        Ok(Self {
            id,
            comment,
            width,
            height,
            max,
            data,
        })
    }

    fn save(&self, path: &str) -> io::Result<()> {
        let f = File::create(path)?;
        let mut writer = io::BufWriter::new(f);
        writer.write_all(format!("{}\n", self.id).as_bytes())?;
        if let Some(comment) = &self.comment {
            writer.write_all(format!("# {}\n", comment).as_bytes())?;
        }
        writer.write_all(format!("{} {}\n", self.width, self.height).as_bytes())?;
        writer.write_all(format!("{}\n", self.max).as_bytes())?;
        writer.write_all(&self.data)?;
        Ok(())
    }
}

impl Steganograpy for PPM {
    fn hide(&mut self, message: &str) -> Result<(), ImageError> {
        let message = message.as_bytes();
        if (message.len() + 1) * 8 > self.data.len() {
            return Err(ImageError::MessageTooLongForImage);
        }
        let message = message.iter().chain(&[b'\0']);
        let all_bytes = self.data.chunks_mut(8);
        for (char, bytes) in message.into_iter().zip(all_bytes) {
            hide_char(*char, bytes);
        }
        Ok(())
    }

    fn reveal(&self) -> String {
        let mut message = String::new();
        let mut all_bytes = self.data.chunks(8);
        loop {
            let bytes = all_bytes.next().unwrap();
            let char = reveal_char(bytes);
            if char == b'\0' {
                break;
            }
            message.push(char as char);
        }
        message
    }
}

#[cfg(test)]
mod tests {
    use crate::{ppm::PPM, steganograpy::Steganograpy, Image};

    #[test]
    fn read_write_ppm() {
        let ppm = PPM::open("images/blue_valknut_mini.ppm").unwrap();
        ppm.save("images/test.ppm").unwrap();
        let ppm_saved = PPM::open("images/test.ppm").unwrap();
        assert_eq!(ppm.id(), ppm_saved.id());
    }

    #[test]
    fn hide_reveal_ppm() {
        let mut ppm = PPM::open("images/blue_valknut_mini.ppm").unwrap();
        ppm.hide("Hello, world!").unwrap();
        let message = ppm.reveal();
        assert_eq!(message, "Hello, world!");
    }
}
