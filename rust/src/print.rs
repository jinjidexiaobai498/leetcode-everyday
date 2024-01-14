//use std::io::Write as IoWrite;
use std::fmt::Write as FmtWrite;
pub fn aprint(v2:&Vec<Vec<i32>>)->String{
    let mut s = String::new();
    for row in v2.iter(){
        
        write!(&mut s,"[").unwrap();
        for e in row.iter(){
            write!(&mut s,"\t{:>4}",e).unwrap();
        }
        writeln!(&mut s,"]").unwrap();
    }
    return s;
}
pub fn aprint_2(v2:&Vec<Vec<i32>>)->String{
    let mut s = String::new();
    for row in v2.iter(){
        
        write!(&mut s,"[").unwrap();
        for e in row.iter(){
            write!(&mut s,"\t{:>4}",e).unwrap();
        }
        writeln!(&mut s,"]").unwrap();
    }
    return s;
}
#[cfg(test)]
mod tests {
    use super::*;
    
    use log::{self, info};
    use log4rs;

    #[test]
    fn test_aprint_v2() {
        let grid = Vec::<Vec<i32>>::from(vec![
                                             vec![0, 2, 0, 0, 0, 0, 0],
                                             vec![0, 0, 0, 2, 2, 1, 0],
                                             vec![0, 2, 0, 0, 1, 2, 0],
                                             vec![0, 0, 2, 2, 2, 0, 2],
                                             vec![0, 0, 0, 0, 0, 0, 0],
            ]);
        aprint(&grid);
        log4rs::init_file("log4rs.yaml", Default::default()).unwrap();
        info!("test aprint");
        
    }
}
