import React, { Component } from 'react';
import { Menu, Sidebar } from 'semantic-ui-react';

import { Link, withRouter } from 'react-router-dom';
import { getMeshViews, getBlockmodelViews, getViewForId } from './views/views';
import { Canvas, DocumentTitle, NavigationBar } from './components';
import { ViewLoader } from './views/ViewLoader';

function buildMenuItemList() {
    return [
        {
            title: 'Meshes',
            items: getMeshViews(),
        },
        {
            title: 'Block Models',
            items: getBlockmodelViews(),
        },
    ];
}

class VizGL extends Component {
    constructor(props) {
        super(props);

        this.loader = new ViewLoader();
        this.state = {
            title: 'minimals',
            sidebarOpened: false,
            isLoading: false,
        };

        this.handleMenuItemSelected = this.handleMenuItemSelected.bind(this);
        this.toggleSidebar = this.toggleSidebar.bind(this);
        this.loadView = this.loadView.bind(this);
    }

    componentDidMount() {
        const viewId = this.props.location.pathname.split('/')[1];
        const view = getViewForId(viewId);

        if (view) {
            this.loadView(viewId);
        }
        this.setState({
            title: view ? view.title : 'minimals',
            isLoading: this.loader.isLoading(),
        });
    }

    toggleSidebar(visible) {
        if (visible !== undefined) {
            this.setState({
                sidebarOpened: visible,
            });
        } else {
            this.setState(prevState => ({
                sidebarOpened: !prevState.sidebarOpened,
            }));
        }
    }

    handleMenuItemSelected(id) {
        this.toggleSidebar(false);
        const view = getViewForId(id);
        this.loadView(view.id);

        this.setState({
            title: view.title,
            isLoading: this.loader.isLoading(),
        });
    }

    loadView(viewId) {
        this.loader.load(viewId).then(() => {
            this.setState({
                isLoading: this.loader.isLoading(),
            });
        });
    }

    generateRoutePath(id) {
        if (process.env.NODE_ENV === 'development' || LOCAL_PRODUCTION) {
            return id;
        }
        return `vizgl/${id}`;
    }

    render() {
        const menuItems = buildMenuItemList().map((section, i) => {
            const { title, items } = section;

            const sectionItems = items.map((item, i) => {
                const toPath = this.generateRoutePath(item.id);
                console.log(toPath);
                return (
                    <Menu.Item
                        key={i}
                        onClick={() => {
                            this.handleMenuItemSelected(item.id);
                        }}
                        as={Link}
                        to={toPath}
                    >
                        {item.title}
                    </Menu.Item>
                );
            });

            return (
                <Menu.Item key={i}>
                    <Menu.Header>{title}</Menu.Header>
                    <Menu.Menu>{sectionItems}</Menu.Menu>
                </Menu.Item>
            );
        });

        return (
            <DocumentTitle title={this.state.title}>
                <Sidebar.Pushable>
                    <Sidebar
                        as={Menu}
                        animation="overlay"
                        inverted
                        vertical
                        onHide={() => {
                            this.toggleSidebar(false);
                        }}
                        visible={this.state.sidebarOpened}
                    >
                        {menuItems}
                    </Sidebar>

                    <Sidebar.Pusher
                        className="app-container"
                        dimmed={this.state.sidebarOpened}
                        style={{ flex: 1 }}
                    >
                        <NavigationBar
                            title={this.state.title}
                            onSidePanelButtonClick={() => this.toggleSidebar()}
                        />
                        <Canvas isLoading={this.state.isLoading} viewTitle={this.state.title} />
                    </Sidebar.Pusher>
                </Sidebar.Pushable>
            </DocumentTitle>
        );
    }
}

const VizGLWithRouter = withRouter(VizGL);
export default VizGLWithRouter;
