/* Created on: Mon Jan 12 13:18:25 2015 */
/* Author: smccrear */

#ifndef _TIMER_
#define _TIMER_


#include <chrono>
#include <functional>
#include <thread>
#include <stdint.h>

namespace toolkit
{

  class Timer {

    public:

      enum options
      {
        ONCE,
        REPEATED,
      };
      
      Timer(int32_t durationInMs, options opt) :
        opt_(opt), 
        timedFunc_(0),
        durationInMs_(durationInMs) { }

      ~Timer() {}

      virtual void Start()
      {
        stopped_ = false;
        while(!stopped_)
        {
          if(opt_ == REPEATED)
          {
            std::this_thread::sleep_until(
                std::chrono::high_resolution_clock::now() 
                + std::chrono::milliseconds(durationInMs_));

            if(timedFunc_)
              timedFunc_();
          }
        }
      }

      void Stop()
      {
        stopped_ = true;
      }
      
      void SetTimedEvent(std::function<void()> timedFunc)
      {
        timedFunc_ = timedFunc;
      }

    private:
      bool stopped_;
      options opt_;
      std::function<void()> timedFunc_;
      std::chrono::milliseconds durationInMs_;

  };

}

#endif  /* _TIMER_ */

/* Example:
 *
 *  Timer * t = new Timer(1000,toolkit::Timer::ONCE);
 *  t->SetTimedEvent(std::bind(&fun));
 * 
 */
