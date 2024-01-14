pub fn add(left: usize, right: usize) -> usize {
    left + right
}
use log::info;
use log4rs;
extern crate libds;

pub fn main() {

    log4rs::init_file("config/log4rs.yaml", Default::default()).unwrap();
    info!("booting up");

    // ...
}
pub mod leetcode;
pub mod print;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
