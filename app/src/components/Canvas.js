import React from 'react';
import { Container, Dimmer } from 'semantic-ui-react';
import { LoadingScreen } from '.';

function buildLoadingMessage(title) {
    return `Loading ${title}`;
}

const Canvas = props => {
    return (
        <Dimmer.Dimmable
            as={Container}
            dimmed={true}
            style={{ flex: 1, width: '100%', margin: 0, padding: 0 }}
        >
            {props.isLoading && <LoadingScreen message={buildLoadingMessage(props.viewTitle)} />}
            <div id="controls" />
            <canvas id="canvas" onContextMenu={event => event.preventDefault()} />
        </Dimmer.Dimmable>
    );
};
export default Canvas;
