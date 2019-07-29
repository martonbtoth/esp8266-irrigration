import {h, render} from 'preact'
import App from './components/App'

let root;

(() => {
   root = render(<App />, document.body, root);
})();
