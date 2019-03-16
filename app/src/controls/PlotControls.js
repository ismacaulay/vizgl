import math from '../utils/math';

class PlotControls {
    constructor(gui, plotApi) {
        this._plotApi = plotApi;
        this._rotationX = 0;
        this._rotationY = 0;
        this._rotationZ = 0;

        this.handleRotationChanged = this.handleRotationChanged.bind(this);

        // const plotFolder = gui.addFolder('Plot');

        gui.add(this, '_rotationX', -90, 90)
            .name('plot rotation x')
            .onChange(this.handleRotationChanged);
        gui.add(this, '_rotationY', -90, 90)
            .name('plot rotation y')
            .onChange(this.handleRotationChanged);
        gui.add(this, '_rotationZ', -90, 90)
            .name('plot rotation z')
            .onChange(this.handleRotationChanged);
    }

    handleRotationChanged() {
        this._plotApi.setRotation([
            math.radians(this._rotationX),
            math.radians(this._rotationY),
            math.radians(this._rotationZ),
        ]);
    }
}
export default PlotControls;
