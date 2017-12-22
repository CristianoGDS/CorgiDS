/*
    CorgiDS Copyright PSISP 2017
    Licensed under the GPLv3
    See LICENSE.txt for details
*/

#ifndef EMUTHREAD_HPP
#define EMUTHREAD_HPP
#include <QMutex>
#include <QThread>
#include "emulator.hpp"

enum DS_KEYS
{
    BUTTON_A,
    BUTTON_B,
    BUTTON_X,
    BUTTON_Y,
    BUTTON_START,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    DEBUGGING
};

enum PAUSE_EVENT
{
    GAME_NOT_STARTED,
    LOADING_ROM,
    OUT_OF_FOCUS,
    MANUAL
};

class EmuThread : public QThread
{
    Q_OBJECT
    private:
        Emulator e;
        QMutex mutex;
        int pause_status;
        bool abort;
        uint32_t upper_buffer[PIXELS_PER_LINE * SCANLINES], lower_buffer[PIXELS_PER_LINE * SCANLINES];
    public:
        explicit EmuThread(QObject* parent = 0);
        int init();
        int load_firmware();
        int load_game(QString ROM_file);
    protected:
        void run() override;
    signals:
        void finished_frame(uint32_t* upper_buffer, uint32_t* lower_buffer);
        void update_FPS(int FPS);
    public slots:
        void shutdown();
        void pause(PAUSE_EVENT event);
        void unpause(PAUSE_EVENT event);
        void press_key(DS_KEYS key);
        void release_key(DS_KEYS key);
        void touchscreen_event(int x, int y);
};

#endif // EMUTHREAD_HPP