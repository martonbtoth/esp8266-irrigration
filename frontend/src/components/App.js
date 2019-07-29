import { h, Component } from 'preact';

const toggle = (status) => {

}

class App extends Component {

    constructor() {
        super();
        this.setState({
            status: "asdf"
        });
        
        this.refresh = this.refresh.bind(this);
        this.toggle = this.toggle.bind(this);
    }

    toggle() {
        let self = this;
        if (this.state.status === 'on') {
            fetch('/off', {method: 'post'}).then(() => self.refresh());
        } else {
            fetch('/on', {method: 'post'}).then(() => self.refresh());
        }
    }

    refresh() {
        let self = this;
        fetch("/status").then(function(response) {
            return response.text();
        }).then(function (text) {
            self.setState({status: text});
        });
    }

    componentDidMount() {
        this.refresh(this);
    }

    render(props, state) {
        return (
        <div>
            <div>
                Status: <span id="status"> {state.status} </span>
            </div>
            <button id="button" onClick={this.toggle}>{state.status == 'on' ? 'Turn off' : 'Turn on'}</button>
        </div>
        );
    }

}

export default App;