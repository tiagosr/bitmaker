#ifndef EMULATORVIEW_H
#define EMULATORVIEW_H

#include <QGLWidget>
#include "libretro.h"

class EmulatorCore: public QObject
{
    Q_OBJECT
public:
    explicit EmulatorCore(std::string core_path);
    void init();
    void deinit();

private:
    void(*_retro_init)(void);
    void(*_retro_deinit)(void);
    unsigned(*_retro_api_version)(void);

    void(*_retro_get_system_info)(struct retro_system_info*info);
    void(*_retro_get_system_av_info)(struct retro_system_av_info*av_info);

    void(*_retro_set_environment)(retro_environment_t env);
    void(*_retro_set_video_refresh)(retro_video_refresh_t video_refresh);
    void(*_retro_set_audio_sample)(retro_audio_sample_t audio_sample);
    void(*_retro_set_audio_sample_batch)(retro_audio_sample_batch_t audio_sample_batch);
    void(*_retro_set_input_poll)(retro_input_poll_t input_poll);
    void(*_retro_set_input_state)(retro_input_state_t input_state);

    void(*_retro_set_controller_port_device)(unsigned port_num, unsigned device_num);

    void(*_retro_reset)(void);
    void(*_retro_run)(void);

    size_t(*_retro_serialize_size)(void);
    bool(*_retro_serialize)(void* data, size_t size);
    bool(*_retro_unserialize)(const void* data, size_t size);

    void(*_retro_cheat_reset)(void);
    void(*_retro_cheat_set)(unsigned index, bool enabled, const char* code);

    bool(*_retro_load_game)(const struct retro_game_info* game);
    bool(*_retro_load_game_special)(unsigned game_type,
          const struct retro_game_info* info, size_t num_info);

    void(*_retro_unload_game)(void);

    unsigned(*_retro_get_region)(void);

    void*(*_retro_get_memory_data)(unsigned);
    size_t(*_retro_get_memory_size)(unsigned);

    void(*_retro_shutdown_game)(void);
};

class EmulatorView : public QGLWidget
{
    Q_OBJECT
public:
    explicit EmulatorView(QWidget *parent = 0, const QGLWidget* shareWidget=0, Qt::WindowFlags f = 0);
    virtual ~EmulatorView();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

signals:

public slots:

};

#endif // EMULATORVIEW_H
