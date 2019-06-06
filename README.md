# Logger
Customizable logger library 

The main goal of this library is to create robust, easy to use and customizable Logger class that could be re-used in several projects to log out different type of messages. It allows not only console logging, but also saving important logs to file or keeping the history of messages. ILogger class and it's subsystems design follows an observer pattern - for better performance of the whole system.

Important: You have to call LOG_Init() before using default logger and LOG_Quit() before exiting the program to free up resources

Messages are split into 5 different categories: ERROR, WARNING, INFO, GENERAL, COMMAND

It allows to quickly diagnose the message - you can just glance over all logs and focus on particular category.
The difference between category meaning is up to user and could be completely customized - when logging a message you decide what category it should have (e.g. when logging an information about attempt of dereferencing a nullptr you could log it as an error) and then the message is logged on all subsystems that are responsible for that type of message.
You can customize which type of message is logged on which subsystem or completely enable/disable logging of particular type of messages.

Logger.h file contains an interface for pre-defined logger object that after initialization is ready to be used across the whole project.
To initialize library you have to call LOG_Init() function and pass in flags describing which subsystem should be initialized.
By default subsystems support following type of messages:
- ConsoleLogger - ERROR, WARNING, INFO, GENERAL
- FileLogger - ERROR
- LogHistory - ERROR, WARNING, INFO, GENERAL, COMMAND

but it can be customized after initialization.

Subsystems are responsible for:
- ConsoleLogger - forwards messages onto console
- FileLogger - saves logs on file (by default only errors, because those are the most likely to stop an application)
- LogHistory - keeps history of all logs chronologically as well as by category of message

Logger.h contains declaration of a logger object that is of type ILogger* and is used to log messages. It is kept as an object pointer instead of separate LOG_function for convinience. To log out message you only have to include Logger.h head and then use log method on that object: logger->log(LOG_MSG_TYPE, msg), log function is designed in fashion of std::cout - you pass in arguments seppareted by comma instead of '<<' (e.g. log(LOG_MSG_GENERAL, "This is example message number ", 1, "!") will log string "This is example message number1!" to all subsytems that support GENERAL type of the message).
ILogger* logger is external and should not be modified by user - every funcionality of that particular object should be modified by corresponding LOG_function. It is not hidden from user for convinience of usage. 

A great feature of this library is that you can create your own subsystems that will be compatible with ILogger class. In order to do that you should create a class that inherits publicly from LOG_Subsystem and then override a pure virtual function called
void updateObserver(const LOG_Subject* subject). In that function you have access to subject class that holds information about a message and type of message (getEventData() and getEventType() methods). You can then attach your new subsytem to logger by calling a LOG_EnableCustomSubsystem(LOG_Subsystem* subsytem, int messageFlags) that will attach it to all message types specified in messageFlags or by calling an attach(LOG_MessageType, LOG_Subsystem* subsystem) method on logger object - though the first method is preffered. It is convinient (you can attach your subsystem to different type of messages at once) and it is more secure.

You can also define your own ILogger object - every neccessary file is included along with Logger.h
You can then freely manage your new object (LOG_functions won't have an effect on it) and attach your new or pre-defined subsystems that are also included with Logger.h, you don't have to call Init/Quit to create your own ILogger object.

Library design is based on that great article about creating logger framework: https://thispointer.com/designing-a-configurable-logging-framework-using-observer-design-pattern/
