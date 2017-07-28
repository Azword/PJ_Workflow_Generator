import {Component} from '@angular/core';

@Component({
    selector: 'home',
    styleUrls: ['./home.component.css'],
    templateUrl: './home.component.html'
})
export class HomeComponent {

    content: String = '';

    private generateGraph(event): void {
        alert(this.content);
    }
}
