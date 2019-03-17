import React from 'react';

export const SidebarMenu = props => {
    const sections = props.items.map((section, i) => {
        const { title, items } = section;
        const sectionItems = items.map((item, i) => {
            return (
                <a key={i} className="item" onClick={() => props.onMenuItemSelected(item.viewId)}>
                    {item.title}
                </a>
            );
        });

        return (
            <div key={i} className="item">
                <div className="header">{title}</div>
                <div className="menu">{sectionItems}</div>
            </div>
        );
    });

    return <div className="ui left sidebar inverted vertical menu overlay">{sections}</div>;
};
