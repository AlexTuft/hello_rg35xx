use std::{
    fs::File,
    io::prelude::*,
    thread,
    time,
};


fn main() -> std::io::Result<()> {
    println!("Hello, RG35XX");

    let mut file = File::create("foo.txt")?;
    file.write_all(b"Hello, world!")?;

    thread::sleep(time::Duration::from_secs(10));

    Ok(())
}
