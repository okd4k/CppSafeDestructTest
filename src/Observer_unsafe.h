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
// File name: Observer_unsafe.h
// Author: okd4k
//


class Observable_unsafe;

class Observer_unsafe {
public:
  Observer_unsafe() {}
  virtual ~Observer_unsafe() {
    subject_->unregister(this);
  }

  Observer_unsafe(const Observer_unsafe&) = delete;
  Observer_unsafe& operator=(const Observer_unsafe&) = delete;

  virtual update() = 0;
  void observe(Observable_unsafe * s) {
    subject_ = s;
    subject_->register_(this);
  }

protected:
  Observable_unsafe *subject_;
};

class Observable_unsafe {
public:
  Observable_unsafe() {}
  virtual ~Observable_unsafe() {}

  Observable_unsafe(const Observable_unsafe&) = delete;
  Observable_unsafe& operator=(const Observable_unsafe&) = delete;

  void register_(Observer_unsafe *observer) {
    std::lock_guard<std::mutex> lock(mutex_);
    observers_.push_back(observer);
  }

  void unregister(Observer_unsafe *observer) {
    std::lock_guard<std::mutex> lock(mutex_);
    observers.erase(observer);
  }

  void notifyObservers() {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto it = observers_.begin(); it != observers_.end(); ++it) {
      it->update();
    }
  }

private:
  mutable std::mutex mutex_;
  std::vector<Observer_unsafe> observers_;

};









