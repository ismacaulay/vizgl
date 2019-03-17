import React from 'react';

export const CanvasContainer = props => {
    return (
        <div className="ui main container canvas-container">
            <div id="controls" />
            <canvas id="canvas" onContextMenu={event => event.preventDefault()} />
        </div>
    );
};
