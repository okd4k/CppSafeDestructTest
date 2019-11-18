// copyright 2019 okd4k

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//
// File name: Observer.cc
// Author: okd4k
//


#include "Observer.h"

void Observer::observe(Observable* s) {
  s->register_(shared_from_this());
  subject_ = s;
}

void Observable::register_(std::weak_ptr<Observer> x) {
  observers_.push_back(x);
}

void Observable::notifyObservers() {
  std::lock_guard<std::mutex> lock(mutex_);
  Iterator it = observers_.begin();
  while(it != observers_.end()) {
    std::shared_ptr<Observer> obj(it->lock());
    if (obj) {
      obj->update();
      ++it;
    }
    else {
      it = observers_.erase(it);
    }
  }
}
