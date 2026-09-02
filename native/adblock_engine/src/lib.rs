#![allow(non_snake_case)]

use adblock::Engine;
use adblock::request::Request;
use std::ffi::{CStr, c_char};

#[no_mangle]
pub extern "C" fn engine_new(rules_ptr: *const c_char) -> *mut Engine {
    let rules = unsafe { CStr::from_ptr(rules_ptr) }.to_string_lossy();
    let engine = Engine::new_with_list_text(rules.to_string());
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

    // adblock 0.13.x added a 4th &str parameter to Request::new (Brave's own
    // benchmarks pass "" for it — exact purpose undocumented, safe default).
    match Request::new(&url, &source, "document", "") {
        Ok(request) => {
            let result = engine.check_network_request(&request);
            // adblock 0.13.x removed BlockerResult::matched. A request is
            // blocked when a filter matched and no exception rule overrides it.
            result.filter.is_some() && result.exception.is_none()
        }
        Err(_) => false,
    }
}

#[no_mangle]
pub extern "C" fn engine_free(engine: *mut Engine) {
    if !engine.is_null() {
        unsafe { drop(Box::from_raw(engine)) };
    }
}
