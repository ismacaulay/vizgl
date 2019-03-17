import React from 'react';
import { Container, Dimmer, Loader } from 'semantic-ui-react';

export const LoadingScreen = props => {
    return (
        <Container>
            <Dimmer active>
                <Loader className="elastic">Loading</Loader>
            </Dimmer>
        </Container>
        // <div className="ui main container">
        //     <div className="ui active dimmer">
        //         <div className="ui elastic text loader">{props.message}</div>
        //     </div>
        // </div>
    );
};
