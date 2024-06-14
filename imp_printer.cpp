#include "imp_printer.hh"

void ImpPrinter::printIndent() {
    for (int i = 0; i < indent; i++) {
        cout << "   ";
    }
}
void ImpPrinter::print(Program* p) {
    cout << "Program : " << endl;
    p->accept(this);
    return;
}

void ImpPrinter::visit(Program* p) {
    cout << "{" << endl;
    p->body->accept(this);
    cout << "}" << endl;
    return;
}

void ImpPrinter::visit(Body * b) {
    b->var_decs->accept(this);
    b->slist->accept(this);
    return;
}

void ImpPrinter::visit(VarDecList* s) {
    list<VarDec*>::iterator it;
    for (it = s->vdlist.begin(); it != s->vdlist.end(); ++it) {
        printIndent();
        (*it)->accept(this);
        cout << ";" << endl;
    }
    return;
}

void ImpPrinter::visit(VarDec* vd) {
    bool first = true;
    cout << "var " << vd->type << " ";
    list<string>::iterator it;
    for (it = vd->vars.begin(); it != vd->vars.end(); ++it){
        if (!first) cout << ", ";
        first = false;
        cout << *it;
    }
    return;
}

void ImpPrinter::visit(StatementList* s) {
    list<Stm*>::iterator it;
    for (it = s->slist.begin(); it != s->slist.end(); ++it) {
        printIndent();

        (*it)->accept(this);
        cout << ";" << endl;
    }
    return;
}

void ImpPrinter::visit(AssignStatement* s) {
    cout << s->id << " = ";
    s->rhs->accept(this);
    return;
}

void ImpPrinter::visit(PrintStatement* s) {
    cout << "print(";
    s->e->accept(this);
    cout << ")";
    return;
}

void ImpPrinter::visit(IfStatement* s) {
    cout << "if (";
    s->cond->accept(this);
    cout << ") then {" << endl;
    indent++;
    s->tbody->accept(this);
    indent--;
    printIndent();
    cout << "}" << endl;
    if (s->fbody!=NULL) {
        printIndent();
        cout << "else {" << endl;
        indent++;
        s->fbody->accept(this);
        indent--;
        printIndent();
        cout << "}" << endl;
    }
    printIndent();
    cout << "endif";
    return;
}

void ImpPrinter::visit(WhileStatement* s) {
    cout << "while (";
    s->cond->accept(this);
    cout << ") do {" << endl;
    indent++;
    s->body->accept(this);
    indent--;
    printIndent();
    cout << "}" << endl;
    printIndent();
    cout << "endwhile";
    return;
}

void ImpPrinter::visit(DoWhileStatement* s) {
    cout << "do {" << endl;
    indent++;
    s->body->accept(this);
    indent--;
    printIndent();
    cout << "} while (";
    s->cond->accept(this);
    cout << ")";
    return;
}

int ImpPrinter::visit(BinaryExp* e) {
    e->left->accept(this);
    cout << ' ' << Exp::binopToString(e->op) << ' ';
    e->right->accept(this);
    return 0;
}



int ImpPrinter::visit(NumberExp* e) {
    cout << e->value;
    return 0;
}

int ImpPrinter::visit(IdExp* e) {
    cout << e->id;
    return 0;
}

int ImpPrinter::visit(ParenthExp* ep) {
    cout << '(';
    ep->e->accept(this);
    cout << ')';
    return 0;
}

int ImpPrinter::visit(CondExp* e) {
    cout << "ifexp(";
    e->cond->accept(this);
    cout << ",";
    e->etrue->accept(this);
    cout << ",";
    e->efalse->accept(this);
    cout << ')';
    return 0;
}
