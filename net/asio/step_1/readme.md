# deadline_timer 

deadline_timer 
 - basic_deadline_timer<boost::posix_time::ptime> 
 - basic_io_object<TimerService> 
   - TimerService를 IoObjectService 타잎으로 받음 
   - 
 - TimerService = deadline_timer_service<Time, TimeTraits> 
   - boost::asio::detail::service_base<deadline_timer_service<TimeType, TimeTraits>>>
     - io_service::service 


asio를 통해 boost의 c++ 사용 패턴을 능숙하게 다루도록 한다. 

