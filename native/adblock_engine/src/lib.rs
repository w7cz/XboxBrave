#![allow(non_snake_case)]

use adblock::Engine;
use std::ffi::{CStr, CString, c_char};

#[no_mangle]
pub extern "C" fn engine_new(rules_ptr: *const c_char) -> *mut Engine {
    let rules = unsafe { CStr::from_ptr(rules_ptr) }.to_string_lossy();
    let filter_set = adblock::lists::FilterSet::new(false);
    let mut engine = Engine::from_filter_set(filter_set, true);
    engine.update_filters(vec![rules.to_string()], vec![]);
    Box::into_raw(Box::new(engine))
}

#[no_mangle]
pub extern "C" fn engine_match(
    engine: *mut Engine,
    url: *const c_char,
    source: *const c_char,
) -> bool {
    let engine = unsafe { &*engine };
    let url = unsafe { CStr::from_ptr(url) }.to_string_lossy();
    let source = unsafe { CStr::from_ptr(source) }.to_string_lossy();
    engine
        .check_network_urls(&url, &source, "")
        .matched
}

#[no_mangle]
pub extern "C" fn engine_free(engine: *mut Engine) {
    if !engine.is_null() {
        unsafe { drop(Box::from_raw(engine)) };
    }
}
