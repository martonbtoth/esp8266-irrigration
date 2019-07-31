import { h, Component } from 'preact';
import Sun from '../Sun/Sun';
import Cloud from '../Cloud/Cloud'

import './App.scss';

class App extends Component {

    render(props, state) {
        return (
        <div className="container">
            <Sun/>
            <Cloud/>
        </div>
        );
    }

}

export default App;