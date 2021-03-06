// cpp-stalin (c) Nikolas Wipper 2021

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "__config"
#ifndef STALIN_CXX_STD_FREESTANDING

#include <ios>

#include <fstream>
#include <iostream>

#ifndef STALIN_CXX_STD_NO_IO
std::filebuf fcin = std::filebuf();
std::filebuf fcout = std::filebuf();
std::filebuf fcerr = std::filebuf();
std::filebuf fclog = std::filebuf();

std::wfilebuf fwcin = std::wfilebuf();
std::wfilebuf fwcout = std::wfilebuf();
std::wfilebuf fwcerr = std::wfilebuf();
std::wfilebuf fwclog = std::wfilebuf();

std::istream std::cin = istream(&fcin);
std::ostream std::cout = ostream(&fcout);
std::ostream std::cerr = ostream(&fcerr);
std::ostream std::clog = ostream(&fclog);

std::wistream std::wcin = wistream(&fwcin);
std::wostream std::wcout = wostream(&fwcout);
std::wostream std::wcerr = wostream(&fwcerr);
std::wostream std::wclog = wostream(&fwclog);
#endif

// This is after the streams to ensure they get initialised first
std::ios_base::Init std::ios_base::init_;

int std::ios_base::Init::init_cnt = 0;
std::ios_base::iea_el *std::ios_base::iea_ = nullptr;
int std::ios_base::iea_size_ = 0;

std::ios_base::~ios_base() {
    emit_event(erase_event);
    free(callbacks_);
}

void std::ios_base::emit_event(ios_base::event ev) {
    for (streamsize i = callback_count_; i > 0; i--) {
        callbacks_[i].ec(ev, *this, callbacks_[i].arg);
    }
}

std::ios_base::fmtflags std::ios_base::flags(ios_base::fmtflags fmtfl) {
    fmtflags t = flags_; // save former value
    flags_ = fmtfl;
    return t;
}

std::ios_base::fmtflags std::ios_base::setf(ios_base::fmtflags fmtfl) {
    fmtflags t = flags_;
    flags_ |= fmtfl;
    return t;
}

std::ios_base::fmtflags std::ios_base::setf(ios_base::fmtflags fmtfl, ios_base::fmtflags mask) {
    fmtflags t = flags_;
    flags_ = (fmtfl & mask) | (flags() & ~mask);
    return t;
}

std::streamsize std::ios_base::precision(streamsize prec) {
    streamsize t = precision_;
    precision_ = prec;
    return t;
}

std::streamsize std::ios_base::width() const {
    return width_;
}

std::streamsize std::ios_base::width(streamsize wide) {
    streamsize t = width_;
    width_ = wide;
    return t;
}

std::locale std::ios_base::imbue(const locale &loc) {
    emit_event(imbue_event);
    locale t = locale_;
    locale_ = loc;
    return t;
}

int std::ios_base::xalloc() {
    int index = iea_size_++;
    iea_ = (iea_el *) realloc(iea_, iea_size_ * sizeof(iea_el));
    return index;
}

long &std::ios_base::iword(int idx) {
    if (idx >= iea_size_) {
        iea_ = (iea_el *) realloc(iea_, (iea_size_ = idx) * sizeof(iea_el));
    }
    return iea_[idx].l;
}

void *&std::ios_base::pword(int idx) {
    if (idx >= iea_size_) {
        iea_ = (iea_el *) realloc(iea_, (iea_size_ = idx) * sizeof(iea_el));
    }
    return iea_[idx].vp;
}

void std::ios_base::register_callback(ios_base::event_callback fn, int index) {
    callbacks_ = (callback *) realloc(callbacks_, ++callback_count_ * sizeof(callback));
    callbacks_[callback_count_ - 1] = callback{
        .ec = fn, .arg = index
    };
}

bool std::ios_base::sync_with_stdio([[maybe_unused]] bool sync) { // Todo
    throw; // Todo: Exceptions
    return false;
}

std::ios_base::Init::Init() {
    if (init_cnt == 0) {
#ifndef STALIN_CXX_STD_NO_IO
        // c's default streams are all buffered
        // but cout/-err/-log should be synced with the default streams
        setbuf(stdin, nullptr);
        setbuf(stdout, nullptr);
        setbuf(stderr, nullptr);

        fcin.__open(stdin, ios_base::in);
        fcout.__open(stdout, ios_base::out);
        fcerr.__open(stderr, ios_base::out);
        fclog.__open(stdout, ios_base::out); // log uses out

        fwcin.__open(stdin, ios_base::in);
        fwcout.__open(stdout, ios_base::out);
        fwcerr.__open(stderr, ios_base::out);
        fwclog.__open(stdout, ios_base::out); // log uses out
#endif
    }
    init_cnt++;
}

std::ios_base::Init::~Init() {
    init_cnt--;
    if (init_cnt == 0) {
#ifndef STALIN_CXX_STD_NO_IO
        cout.flush();
        cerr.flush();
        clog.flush();

        wcout.flush();
        wcerr.flush();
        wclog.flush();
#endif
    }
}

std::ios_base &std::boolalpha(ios_base &str) {
    str.setf(ios_base::boolalpha);
    return str;
}

std::ios_base &std::showbase(ios_base &str) {
    str.setf(ios_base::showbase);
    return str;
}

std::ios_base &std::showpoint(ios_base &str) {
    str.setf(ios_base::showpoint);
    return str;
}

std::ios_base &std::showpos(ios_base &str) {
    str.setf(ios_base::showpos);
    return str;
}

std::ios_base &std::skipws(ios_base &str) {
    str.setf(ios_base::skipws);
    return str;
}

std::ios_base &std::unitbuf(ios_base &str) {
    str.setf(ios_base::unitbuf);
    return str;
}

std::ios_base &std::uppercase(ios_base &str) {
    str.setf(ios_base::uppercase);
    return str;
}

std::ios_base &std::noboolalpha(ios_base &str) {
    str.unsetf(ios_base::boolalpha);
    return str;
}

std::ios_base &std::noshowbase(ios_base &str) {
    str.unsetf(ios_base::showbase);
    return str;
}

std::ios_base &std::noshowpoint(ios_base &str) {
    str.unsetf(ios_base::showpoint);
    return str;
}

std::ios_base &std::noshowpos(ios_base &str) {
    str.unsetf(ios_base::showpos);
    return str;
}

std::ios_base &std::noskipws(ios_base &str) {
    str.unsetf(ios_base::skipws);
    return str;
}

std::ios_base &std::nounitbuf(ios_base &str) {
    str.unsetf(ios_base::unitbuf);
    return str;
}

std::ios_base &std::nouppercase(ios_base &str) {
    str.unsetf(ios_base::uppercase);
    return str;
}

std::ios_base &std::dec(ios_base &str) {
    str.setf(ios_base::dec);
    return str;
}

std::ios_base &std::hex(ios_base &str) {
    str.setf(ios_base::hex);
    return str;
}

std::ios_base &std::oct(ios_base &str) {
    str.setf(ios_base::oct);
    return str;
}

std::ios_base &std::fixed(ios_base &str) {
    str.setf(ios_base::fixed);
    return str;
}

std::ios_base &std::scientific(ios_base &str) {
    str.setf(ios_base::scientific);
    return str;
}

std::ios_base &std::hexfloat(ios_base &str) {
    str.setf(ios_base::fixed | ios_base::scientific);
    return str;
}

std::ios_base &std::defaultfloat(ios_base &str) {
    str.unsetf(ios_base::floatfield);
    return str;
}

#endif // ifndef STALIN_CXX_STD_FREESTANDING
