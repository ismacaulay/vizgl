import React, { Component } from 'react';
import { BrowserRouter as Router, Route } from 'react-router-dom';
import { getMeshViews, getBlockmodelViews, getViewForId } from './views/views';
import VizGL from './VizGL';

class App extends Component {
    buildRoutes() {
        const index = <Route key="index" path="/" exact />;
        const viewRoutes = [...getMeshViews(), ...getBlockmodelViews()].map(view => {
            <Route key={view.id} path={view.id} exact />;
        });

        return [index, viewRoutes];
    }

    render() {
        const routes = this.buildRoutes();

        return (
            <Router>
                <VizGL />
                {routes}
            </Router>
        );
    }
}

export default App;
