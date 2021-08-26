extern crate rand;
use rand::{Rng, thread_rng};

extern crate sdl2;
use sdl2::pixels::Color;
use sdl2::event::Event;

use std::time::{Duration, Instant};

const fn cell_size() -> usize {2}
const fn matrix_size() -> (usize, usize) {(500, 500)}
// type Matrix     = [[i32; matrix_size().0]; matrix_size().1];
type Matrix     = Vec<[i32; matrix_size().0]>;
type RectMatrix = [[sdl2::rect::Rect; matrix_size().0]; matrix_size().1];

fn init_rand_matrix() -> Matrix {
    let mut rng = thread_rng();
    let mut arr =  vec![[0; matrix_size().0]; matrix_size().1];
    for j in 0..matrix_size().1 {
        for i in 0..matrix_size().0 {
            arr[j][i] = rng.gen_range(0..=1);
        }
    }
    arr
}

fn adjacent(arr: &Matrix, row: i32, col: i32) -> i32 {
    let mut adj_val = 0;
    for r in row-1..=row+1 {
        for c in col-1..=col+1 {
            if r>=0 && c>=0 {
                adj_val += arr.get(r as usize).unwrap_or(&[0; matrix_size().0]).get(c as usize).unwrap_or(&0);
            }
        }
    }
    adj_val
}

fn init_rects() -> RectMatrix {
    let mut rec = [[sdl2::rect::Rect::new(0, 0, 1, 1); matrix_size().0]; matrix_size().1]; 
    for j in 0..matrix_size().1 {
        for i in 0..matrix_size().0 {
            rec[j][i] = sdl2::rect::Rect::new((i * cell_size()) as i32, (j * cell_size()) as i32, cell_size() as u32, cell_size() as u32);
        }
    }
    rec
}

fn main() {
    // SDL2 init
    let sdl_context  = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();
    let window = video_subsystem.window("Conway's Game of Life", (cell_size()*matrix_size().0) as u32, (cell_size()*matrix_size().1) as u32).position_centered().build().unwrap();
    let mut event_pump = sdl_context.event_pump().unwrap();
    // prepare canvas
    let mut io = window.into_canvas().accelerated().build().unwrap();
    io.set_draw_color(Color::BLACK);
    io.clear();
    io.present();
    let rects = init_rects(); 
    // init
    let mut grid = init_rand_matrix(); 
    let mut change_grid = vec![[0; matrix_size().0]; matrix_size().1]; 
    let mut timer = Instant::now();
    let ms_per_frame: u64 = 100;

    'main: loop {
        // Escape event
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit{..} => {break 'main},
                _ => {},
            }
        }
        // Drawing and Simulation
        io.set_draw_color(Color::WHITE);
        for j in 0..matrix_size().1 {
            for i in 0..matrix_size().0 {
                match adjacent(&grid, j as i32, i as i32) {
                    3 => {change_grid[j][i] = 1; io.fill_rect(rects[j][i]).unwrap()},
                    _ => change_grid[j][i] = 0,
                }
            }
        }
        // Presentation
        io.present();
        io.set_draw_color(Color::BLACK);
        io.clear();

        grid = change_grid.clone();
        change_grid = vec![[0; matrix_size().0]; matrix_size().1];
        
        if timer.elapsed().as_millis() < ms_per_frame as u128 {
            std::thread::sleep(Duration::from_millis(ms_per_frame - timer.elapsed().as_millis() as u64));
        }
        timer = Instant::now();
    }
}
