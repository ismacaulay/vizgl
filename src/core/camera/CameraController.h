#pragma once

class I_CameraControls;

class CameraController
{
public:
    explicit CameraController(I_CameraControls& cameraControls);
    ~CameraController() = default;

    void start(int button, int x, int y);
    void zoom(double delta);
    void update(int x, int y);
    void finish();

private:
    I_CameraControls& cameraControls_;
    bool inProgress_;
};
