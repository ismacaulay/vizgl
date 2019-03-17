import React from 'react';
import { Icon, Menu, Container } from 'semantic-ui-react';

const NavigationBar = props => {
    return (
        <Container className="navigation-container">
            <Menu fixed="top" inverted>
                <Menu.Item onClick={props.onSidePanelButtonClick}>
                    <Icon name="content" />
                </Menu.Item>
                <Menu.Item>{props.title}</Menu.Item>
            </Menu>
        </Container>
    );
};
export default NavigationBar;
