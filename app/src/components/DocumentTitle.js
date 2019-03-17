import React from 'react';

function buildTitle(title) {
    return `vizgl | ${title}`;
}

const DocumentTitle = props => {
    document.title = buildTitle(props.title);
    return <>{props.children}</>;
};
export default DocumentTitle;
