import { h, Component } from 'preact';

import './Cloud.scss';

class Cloud extends Component {

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
            self.setState({status: 'off'})
        } else {
            fetch('/on', {method: 'post'}).then(() => self.refresh());
            self.setState({status: 'on'})
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

    render() {
        return (
            <div className="cloud">
                <svg onClick={this.toggle} height="463pt" className={'cloud-sub-1 ' + this.state.status} viewBox="0 0 463.83425 463" width="463pt" xmlns="http://www.w3.org/2000/svg">
                    <path className="cloud-path" d="m375.835938 112.957031c-5.851563 0-11.691407.582031-17.425782 1.742188-4.324218-21.582031-18.304687-39.992188-37.933594-49.957031-19.625-9.964844-42.738281-10.382813-62.714843-1.136719-18.078125-49.796875-73.101563-75.507813-122.898438-57.429688s-75.507812 73.105469-57.429687 122.898438c-43.621094 1.378906-78.078125 37.484375-77.4257815 81.121093.6562495 43.640626 36.1835935 78.691407 79.8281255 78.761719h296c48.597656 0 88-39.398437 88-88 0-48.601562-39.402344-88-88-88zm0 0"/>
                </svg>
                <svg onClick={this.toggle} height="463pt" className={'cloud-main ' + this.state.status} viewBox="0 0 463.83425 463" width="463pt" xmlns="http://www.w3.org/2000/svg">
                    <path className="cloud-path" d="m375.835938 112.957031c-5.851563 0-11.691407.582031-17.425782 1.742188-4.324218-21.582031-18.304687-39.992188-37.933594-49.957031-19.625-9.964844-42.738281-10.382813-62.714843-1.136719-18.078125-49.796875-73.101563-75.507813-122.898438-57.429688s-75.507812 73.105469-57.429687 122.898438c-43.621094 1.378906-78.078125 37.484375-77.4257815 81.121093.6562495 43.640626 36.1835935 78.691407 79.8281255 78.761719h296c48.597656 0 88-39.398437 88-88 0-48.601562-39.402344-88-88-88zm0 0"/>
                </svg>
                <svg onClick={this.toggle} height="463pt" className={'cloud-sub-2 ' + this.state.status} viewBox="0 0 463.83425 463" width="463pt" xmlns="http://www.w3.org/2000/svg">
                    <path className="cloud-path" d="m375.835938 112.957031c-5.851563 0-11.691407.582031-17.425782 1.742188-4.324218-21.582031-18.304687-39.992188-37.933594-49.957031-19.625-9.964844-42.738281-10.382813-62.714843-1.136719-18.078125-49.796875-73.101563-75.507813-122.898438-57.429688s-75.507812 73.105469-57.429687 122.898438c-43.621094 1.378906-78.078125 37.484375-77.4257815 81.121093.6562495 43.640626 36.1835935 78.691407 79.8281255 78.761719h296c48.597656 0 88-39.398437 88-88 0-48.601562-39.402344-88-88-88zm0 0"/>
                </svg>
            </div>
            );
    }

}

export default Cloud;