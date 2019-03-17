import React from 'react';

export const View = () => {
    return (
        <div className="canvas-container">
            <div id="controls" />
            <canvas id="canvas" onContextMenu={event => event.preventDefault()} />
        </div>
    );
};
