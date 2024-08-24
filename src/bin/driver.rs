use steganograpy::{ppm::PPM, steganograpy::Steganograpy, Image};

use clap::Parser;

/// Simple program to greet a person
#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    /// path to the read the image
    #[arg(short, long)]
    load_path: String,

    /// message to hide
    #[arg(short, long)]
    message: Option<String>,

    /// path to the save the image
    #[arg(short, long)]
    save_path: Option<String>,
}

fn main() {
    let args = Args::parse();
    if let Some(message) = args.message {
        let mut image = PPM::open(&args.load_path).unwrap();
        image.hide(&message).unwrap();
        if let Some(save_path) = args.save_path {
            image.save(&save_path).unwrap();
        } else {
            image.save(&args.load_path).unwrap();
        }
    } else {
        let image = PPM::open(&args.load_path).unwrap();
        println!("{}", image.reveal());
    }
}
