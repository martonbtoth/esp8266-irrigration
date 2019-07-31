import { h, Component } from 'preact';

import './Sun.scss';

export default () => {
    return (
    <div className="sun">
        <div className="sun-ray-1"></div>
        <div className="sun-ray-2"></div>
        <div className="sun-ray-3"></div>
        <div className="sun-ray-4"></div>
        <div className="sun-body"></div>
    </div>
    );
}