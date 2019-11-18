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
// File name: Observer.h
// Author: okd4k
//

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>
#include <mutex>
#include <memory>

class Observable;

class Observer : std::enable_shared_from_this<Observer> {
public:
  Observer() {}
  virtual ~Observer() {}

  Observer(const Observer&) = delete;
  Observer& operator=(const Observer&) = delete;

  virtual void update() = 0;
  void observe(Observable* s);

protected:
  Observable* subject_;

};

class Observable {
public:
  void register_(std::weak_ptr<Observer> x);
  void notifyObservers();

private:
  mutable std::mutex mutex_;
  std::vector<std::weak_ptr<Observer> > observers_;
  typedef std::vector<std::weak_ptr<Observer> >::iterator Iterator;
  
};

#endif
