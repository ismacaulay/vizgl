import math from '../utils/math';

class PlotControls {
    constructor(gui, plotApi) {
        this._plotApi = plotApi;
        this._xRotation = 0;
        this._yRotation = 0;
        this._zRotation = 0;

        this.handleRotationChanged = this.handleRotationChanged.bind(this);

        this._xRotationController = gui
            .add(this, '_xRotation', -90, 90)
            .name('plot rotation x')
            .onChange(this.handleRotationChanged);
        this._yRotationController = gui
            .add(this, '_yRotation', -90, 90)
            .name('plot rotation y')
            .onChange(this.handleRotationChanged);
        this._zRotationController = gui
            .add(this, '_zRotation', -90, 90)
            .name('plot rotation z')
            .onChange(this.handleRotationChanged);
    }

    handleRotationChanged() {
        this._plotApi.setRotation([
            math.radians(this._xRotation),
            math.radians(this._yRotation),
            math.radians(this._zRotation),
        ]);
    }

    reset() {
        this._xRotationController.setValue(0);
        this._yRotationController.setValue(0);
        this._zRotationController.setValue(0);
    }
}
export default PlotControls;
