import React from 'react';

export const NavigationBar = props => {
    return (
        <div className="ui fixed inverted menu">
            <a className="item icon" onClick={props.onMenuButtonClick}>
                <i className="content icon" />
            </a>
        </div>
    );
};
