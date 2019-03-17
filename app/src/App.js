import React, { Component } from 'react';
import {
    Header,
    Icon,
    Image,
    Menu,
    Segment,
    Sidebar,
    Container,
    Dimmer,
    Loader,
    Item,
} from 'semantic-ui-react';

import { LoadingScreen } from './components/LoadingScreen';
import { SidebarMenu } from './components/SidebarMenu';
import { NavigationBar } from './components/NavigationBar';
import { Cube } from './meshes';
import { BrowserRouter as Router, Route, Link } from 'react-router-dom';
import { getMeshViews, getBlockmodelViews, getViewForId } from './views/views';

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

class App extends Component {
    constructor(props) {
        super(props);

        this.state = {
            title: undefined,
            sidebarOpened: false,
            isLoading: true,
        };

        this.handleMenuItemSelected = this.handleMenuItemSelected.bind(this);
        this.toggleSidebar = this.toggleSidebar.bind(this);
        this.buildRoutes = this.buildRoutes.bind(this);
    }

    toggleSidebar(visible) {
        this.setState({
            sidebarOpened: visible,
        });
    }

    handleMenuItemSelected(id) {
        this.toggleSidebar(false);
        const view = getViewForId(id);

        this.setState({
            title: view.title,
        });
    }

    buildRoutes() {
        const index = <Route key="index" path="/" exact />;
        const viewRoutes = [...getMeshViews(), ...getBlockmodelViews()].map(view => {
            <Route key={view.id} path={view.id} exact />;
        });

        return [index, viewRoutes];
    }

    render() {
        const menuItems = buildMenuItemList().map((section, i) => {
            const { title, items } = section;

            const sectionItems = items.map((item, i) => {
                return (
                    <Menu.Item
                        key={i}
                        onClick={() => {
                            this.handleMenuItemSelected(item.id);
                        }}
                        as={Link}
                        to={item.id}
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

        const routes = this.buildRoutes();

        const title = this.state.title || 'minimals';
        document.title = `vizgl | ${title}`;

        return (
            <Router>
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
                        <Container className="navigation-container">
                            <Menu fixed="top" inverted>
                                <Menu.Item
                                    onClick={() => {
                                        this.toggleSidebar(true);
                                    }}
                                >
                                    <Icon name="content" />
                                </Menu.Item>
                            </Menu>
                        </Container>
                        <Container className="canvas-container">
                            {/* <div id="controls" /> */}
                            {/* <canvas id="canvas" onContextMenu={event => event.preventDefault()} /> */}
                            {this.state.isLoading && <LoadingScreen />}
                        </Container>
                    </Sidebar.Pusher>
                </Sidebar.Pushable>

                {routes}
            </Router>
        );
    }
}

export default App;
