import React from 'react';
import { Dimmer, Loader } from 'semantic-ui-react';

const LoadingScreen = props => {
    return (
        <Dimmer active={true} style={{ width: '100%', margin: 0, padding: 0 }}>
            <Loader active={true} className="elastic">
                {props.message}
            </Loader>
        </Dimmer>
    );
};
export default LoadingScreen;
