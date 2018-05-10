#ifndef IOBSERVER_H
#define IOBSERVER_H


namespace common
{
    namespace observer
    {
        class IObserver
        {
        public:
            virtual ~IObserver() = default;
            virtual void update() = 0;
        };

    }
}


#endif // IOBSERVER_H
